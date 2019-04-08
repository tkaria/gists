"""
Called via SQS message from lambda function that receives site text so that we can 
process keywords on an EC2 instance and return the file to the next bucket in the pipeline

For a little more on why this couldn't go into Lambda see:
https://medium.freecodecamp.org/escaping-lambda-function-hell-using-docker-40b187ec1e48
https://serverlesscode.com/post/deploy-scikitlearn-on-lamba/
"""

from __future__ import print_function
import logging
import os
import boto3
import botocore
import settings
import viq_metadata
import viq_keywords_elastic
import sys
import json

LOGGER = logging.getLogger('QueueDumper')
logging.basicConfig(level=logging.DEBUG, format='%(asctime)s -%(name)s - $%(levelname)s - %(message)s')
logging.getLogger('boto3').setLevel(logging.WARNING)
logging.getLogger('botocore').setLevel(logging.WARNING)
logging.getLogger('nose').setLevel(logging.WARNING)
logging.getLogger('s3transfer').setLevel(logging.CRITICAL)

S3_CLIENT = boto3.client('s3')
LAMBDA_CLIENT = boto3.client('lambda')
SQS_CLIENT=boto3.resource('sqs')



def handler():
    """
    AWS handler for inserting already keyworded documents that arrive via SQS into Elasticsearch
    """

    while 1:
        try:
            # queue = SQS_CLIENT.get_queue_by_name(QueueName='ventureiq-lambda-pipeline-elastic-insert')
            queue = SQS_CLIENT.get_queue_by_name(QueueName='ventureiq-lambda-pipeline')
            LOGGER.debug(queue)
            for message in queue.receive_messages(MessageAttributeNames=['key', 'bucket', 'type', 'instruction']):
                LOGGER.debug('Received message with attributes: {}'.format(message.message_attributes))
                key = message.message_attributes.get('key').get('StringValue')
                bucket = message.message_attributes.get('bucket').get('StringValue') 
                msg_type = message.message_attributes.get('type').get('StringValue') 
                instruction = message.message_attributes.get('instruction').get('StringValue') 
                if instruction == 'insert-keywords':
                    LOGGER.debug('Processing: {} {} {} {}'.format(key, bucket, msg_type, instruction))
                    download_path = os.path.join(settings.META_DIR, key)
                    S3_CLIENT.download_file(bucket, key, download_path)
        except botocore.exceptions.ClientError as boto_error:
            LOGGER.warn('Boto Error: {}'.format(boto_error))
        except OSError as os_error:
            LOGGER.warn('OS Error: {}'.format(os_error))


if __name__ == '__main__':
        LOGGER.info('Waiting ...')
        handler()


